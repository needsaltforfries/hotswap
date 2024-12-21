#include "Hotswap.h"

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
        std::cout << "\tAttempting reload...\n";
        Reload();
        // std::cout << "\tReload finished!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
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
        FARPROC get_state = GetProcAddress(this->library, "GetState");
        GameState* prevState = (GameState*)((*(funcPtr)get_state)(nullptr));
        std::cout << "got state at " << prevState << std::endl;
        std::vector<Object*> objCopy = prevState->objects;
        //free memory
        free(prevState);
        FreeLibrary(this->library);
        Load();
        //copy state over to new state
        FARPROC set_state = GetProcAddress(this->library, "SetState");
        GameState* newState = (GameState*)malloc(1024);
        newState->objects = objCopy;
        void* result = (*(funcPtr)set_state)(newState);
        std::cout << "attempted to call " << result << std::endl;
        LWT = CWT;
        isReloading = false;
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