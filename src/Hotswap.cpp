#include "Hotswap.h"
#include "assets/GameHeader.h"

Hotswap::Hotswap(){
    finishPoll = false;
    isReloading = false;
    delayReloadFlag = false;
}

Hotswap::~Hotswap(){
}

void Hotswap::pollThread(){
    //poll reload
    while(!finishPoll){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "\tAttempting reload...\n";
        Reload();
        // std::cout << "\tReload finished!" << std::endl;
    }
}

void Hotswap::Init(){
    Load();
    ptPtr = new std::thread(&Hotswap::pollThread, this);
}

void Hotswap::Terminate(){
    finishPoll = true;
    std::cout << "joining thread\n";
    ptPtr->join();
    std::cout << "thread joined\n";
    if(ptPtr != nullptr)
        delete ptPtr;
    FreeLibrary(this->library);
    std::cout << "Hotswap terminated." << std::endl;
}

void Hotswap::Load(){
    
    //create a copy of the library
    std::filesystem::path src(lib_path);
    std::filesystem::path cpy(cpy_path);

    try {
        //copy library into ./gen/<cpy_path>
        std::filesystem::create_directories("./gen");
        if (std::filesystem::exists(cpy)) {
            std::filesystem::remove(cpy);
        }
        std::filesystem::copy(src, cpy, std::filesystem::copy_options::overwrite_existing);
        std::cout << "file copied!\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "error while copying: " << e.what() << '\n';
    }

    //load copied library at runtime
    this->library = LoadLibraryA(cpy_path.c_str());
    std::cout << "library linked!" << std::endl;
}

void Hotswap::Reload(){
    
    //update lib if it has been modified
    std::lock_guard<std::mutex> lock(mtx);
    auto CWT = std::filesystem::last_write_time(lib_path);
    if(CWT > LWT){
        isReloading = true;
        std::cout << "waiting to reload lib." << std::endl;
        while(delayReloadFlag){
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        //prepare to copy state
        funcPtr get_state = (funcPtr)func("GetState");
        funcPtr blank_obj = (funcPtr)func("BlankObj");
        GameState* prevState = (GameState*)((*get_state)(nullptr));
        std::cout << "copying objects...\n";
        // funcPtr2 CopyObject = (funcPtr2)func("CopyObject");
        
        std::vector<Object*> objCopy(prevState->objects.size());
        std::vector<Object*>* prevObj = &prevState->objects;
        for(size_t i = 0; i < prevObj->size(); ++i){
            objCopy[i] = (Object*)blank_obj(prevObj->at(i));
            objCopy[i]->id = prevObj->at(i)->id;
            objCopy[i]->renderData = prevObj->at(i)->renderData;
            objCopy[i]->vertShaderPath = prevObj->at(i)->vertShaderPath;
            objCopy[i]->fragShaderPath = prevObj->at(i)->fragShaderPath;
            free(prevState->objects[i]);
            std::cout << "Copying " << objCopy[i]->id << "...\n";
        }
        std::cout << "objects copied\n";
        std::map<unsigned int, void*>* mapCopy = prevState->obj_vis_map;
        *mapCopy = *prevState->obj_vis_map;
        //free lib
        FreeLibrary(library);
        Load();
        //copy state over to new state
        GameState* newState = (GameState*)((*get_state)(nullptr));
        std::cout << "newState: " << &newState->objects << " " << &newState->obj_vis_map << "\n";
        for(size_t i = 0; i < objCopy.size(); ++i){
            *newState->objects[i] = *objCopy[i];
            std::cout << "Transferring " << newState->objects[i]->id << "...\n";
            free(objCopy[i]);
        }
        *newState->obj_vis_map = *mapCopy;
        std::cout << "objects transfered\n";
        LWT = CWT;
        isReloading = false;
        std::cout << "Hotswap finished." << std::endl;
    }
}

void* Hotswap::LoadDLLFunc(std::string funcName){
    FARPROC proc = GetProcAddress(this->library, funcName.c_str());
    assert(proc != NULL);
    return (void*)proc;
}

void* Hotswap::func(std::string funcName){
    return LoadDLLFunc(funcName);
}

bool Hotswap::reloadStatus(){
    return isReloading;
}