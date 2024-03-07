#pragma once

//struct FrameContext2 {
//	ComPtr<IDXGISurface1> surface = nullptr;
//	ComPtr<ID3D11Resource> resource11 = nullptr;
//	ComPtr<ID2D1Bitmap1> d2dRenderTarget = nullptr;
//	ComPtr<ID2D1Bitmap> backBuffer = nullptr;
//	ComPtr<ID2D1Effect> blur = nullptr;
//};
//
//std::unique_ptr<FrameContext2[]> gameFrameContext;
//
//void Create2D2RenderContext() {
//	int buffersCounts = d3d12hook::buffersCounts;
//	auto d3d12Device = d3d12hook::d3d12Device;
//	auto d3d12DescriptorHeapBackBuffers = d3d12hook::d3d12DescriptorHeapBackBuffers;
//	auto pSwapChain = d3d12hook::_pSwapChain;
//	auto d3d11On12Device = d3d12hook::d3d11On12Device;
//	auto d2d1DeviceContext = d3d12hook::d2d1DeviceContext;
//
//	gameFrameContext = std::unique_ptr<FrameContext2[]>(new FrameContext2[buffersCounts]);
//
//	const auto rtvDescriptorSize = d3d12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
//	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = d3d12DescriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();
//
//	for (size_t i = 0; i < buffersCounts; i++) {
//		ComPtr<ID3D12Resource> pBackBuffer;
//
//		pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
//
//		if (d3d11On12Device.Get() != nullptr && gameFrameContext[i].resource11.Get() == nullptr) {
//			D3D11_RESOURCE_FLAGS d3d11Flags = { D3D11_BIND_RENDER_TARGET };
//			d3d11On12Device->CreateWrappedResource(
//				pBackBuffer.Get(),
//				&d3d11Flags,
//				D3D12_RESOURCE_STATE_RENDER_TARGET,
//				D3D12_RESOURCE_STATE_PRESENT,
//				IID_PPV_ARGS(&gameFrameContext[i].resource11));
//
//			gameFrameContext[i].resource11.As(&gameFrameContext[i].surface);
//
//			float dpi = (float)GetDpiForSystem();
//			D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
//				D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
//				D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
//				dpi,
//				dpi);
//
//			d2d1DeviceContext->CreateBitmapFromDxgiSurface(
//				gameFrameContext[i].surface.Get(),
//				&bitmapProperties,
//				&gameFrameContext[i].d2dRenderTarget
//			);
//		}
//	}
//}
//
//void RenderBlur() {
//	//auto _lock = std::lock_guard(lock);
//	auto pSwapChain = d3d12hook::_pSwapChain;
//	auto d2d1DeviceContext = d3d12hook::d2d1DeviceContext;
//	auto d3d11On12Device = d3d12hook::d3d11On12Device;
//	auto d3d11ImmediateContext = d3d12hook::d3d11ImmediateContext;
//
//	FrameContext2& currentFrameContext = gameFrameContext[pSwapChain->GetCurrentBackBufferIndex()];
//
//	if (d2d1DeviceContext.Get() != nullptr) {
//		const auto d3d11Resources = currentFrameContext.resource11.Get();
//
//		if (d3d11Resources != nullptr && d3d11On12Device.Get() != nullptr && d3d11ImmediateContext.Get() != nullptr) {
//			d3d11On12Device->AcquireWrappedResources(&d3d11Resources, 1);
//
//			d2d1DeviceContext->SetTarget(currentFrameContext.d2dRenderTarget.Get());
//			d2d1DeviceContext->BeginDraw();
//			d3d12hook::CopyBitmap(d2d1DeviceContext.Get(), currentFrameContext.d2dRenderTarget, currentFrameContext.backBuffer);
//
//			if (currentFrameContext.blur.Get() == nullptr) {
//				d2d1DeviceContext->CreateEffect(CLSID_D2D1DirectionalBlur, &currentFrameContext.blur);
//				currentFrameContext.blur->SetInput(0, currentFrameContext.backBuffer.Get());
//
//				currentFrameContext.blur->SetValue(D2D1_DIRECTIONALBLUR_PROP_STANDARD_DEVIATION, 10.0f);
//				currentFrameContext.blur->SetValue(D2D1_DIRECTIONALBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
//			}
//			d2d1DeviceContext->DrawImage(currentFrameContext.blur.Get());
//
//			d2d1DeviceContext->EndDraw();
//
//			d3d11On12Device->ReleaseWrappedResources(&d3d11Resources, 1);
//			d3d11ImmediateContext->Flush();
//		}
//	}
//}