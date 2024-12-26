#pragma once

#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <assert.h>
#include <thread>
#include <mutex>
#include <atomic>

typedef void *(*funcPtr) (void *);

const std::string lib_path = "./gamelib.dll";
const std::string cpy_path = "./gen/gamelib_cpy.dll";

static auto LWT = std::filesystem::last_write_time(lib_path);

class Hotswap{
    public:
        //methods
        Hotswap();
        ~Hotswap();
        void Init();
        void Terminate();
        void Load();
        void Reload();
        void* func(std::string funcName);
        bool reloadStatus();
        bool delayReloadFlag;
    private:
        HMODULE library;
        std::thread* ptPtr;
        std::atomic_bool finishPoll;
        std::atomic_bool isReloading;
        std::mutex mtx;
        void pollThread();
};