#include "include.h"

void InitHooks() {
	mainWindow = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");

	InitGameHooks();

	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {}
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {}
	kiero::bind(54, (void**)&d3d12hook::oExecuteCommandListsD3D12, d3d12hook::hookExecuteCommandListsD3D12);
	kiero::bind(58, (void**)&d3d12hook::oSignalD3D12, d3d12hook::hookSignalD3D12);
	//kiero::bind(134, (void**)&d3d12hook::oReleaseD3D12, d3d12hook::HookReleaseD3D12);
	kiero::bind(140, (void**)&d3d12hook::oPresentD3D12, d3d12hook::hookPresentD3D12);
	kiero::bind(145, (void**)&d3d12hook::oResizeBuffersD3D12, d3d12hook::HookResizeBuffersD3D12);
	kiero::bind(84, (void**)&d3d12hook::oDrawInstancedD3D12, d3d12hook::hookkDrawInstancedD3D12);
	kiero::bind(85, (void**)&d3d12hook::oDrawIndexedInstancedD3D12, d3d12hook::hookDrawIndexedInstancedD3D12);

	do {
		Sleep(1000);
	} while (running);

	module_manager.Delete();
	d3d12hook::ReleaseRender();
	kiero::shutdown();
	d3d12hook::Remove(mainWindow);
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
	FreeLibraryAndExitThread(mainModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		FILE* pConsoleStream;
		freopen_s(&pConsoleStream, "CONOUT$", "w", stdout);

		mainModule = hModule;

		HMODULE moduleHandle = GetModuleHandle(nullptr);
		MODULEINFO moduleInfo = {};

		GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(moduleInfo));

		mStart = (uintptr_t)moduleHandle;
		mEnd = mStart + moduleInfo.SizeOfImage;

		//std::cout << (uintptr_t)(FindSig("DC 42 ? ? ? ? 00 00 70 42 6F 12 83 3A 00 00 00 00") + 2) << std::endl;

		InitAddresses();
		module_manager.Init();

		/*InitImguiHooks();
		InitGameHooks();*/

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitHooks, hModule, 0, 0);
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitGameHooks, hModule, 0, 0);

		dbg_console.Print("Client injected successfully!");
		dbg_console.Print("Press DEL to uninject.");
		dbg_console.Print("Press INSERT to show/hide menu.");
	}
	return TRUE;
}