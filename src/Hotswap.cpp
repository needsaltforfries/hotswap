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
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "\tAttempting reload...\n";
        Reload();
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
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        
        funcPtr get_state = (funcPtr)func("GetGameState");
        void* state = (*get_state)(nullptr);

        funcPtr get_lib = (funcPtr)func("GetObjectLib");
        void* obj_lib = (*get_lib)(nullptr);

        //free lib
        FreeLibrary(library);
        Load(); 

        //re-init lib
        void* params[] = {state, obj_lib};
        (*(funcPtr)func("Init"))(params);

        LWT = CWT;
        isReloading = false;
        std::cout << "Hotswap finished." << std::endl;
    }
}

void* Hotswap::func(std::string funcName){
    FARPROC proc = GetProcAddress(this->library, funcName.c_str());
    assert(proc != NULL);
    return (void*)proc;
}

bool Hotswap::reloadStatus(){
    return isReloading;
}