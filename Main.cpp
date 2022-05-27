#include "stdafx.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    const wchar_t AppName[] = L"Win32 Window";

    // Register the window class.

    WNDCLASS wc = { };

    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = AppName;

    RegisterClass(&wc);

    RECT rc = {0, 0, 640, 480};
 
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        AppName,                        // Window class
        AppName,                        // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) return 0;

    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_9_1,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1
    };

    D3D_FEATURE_LEVEL m_featureLevel;

    // This flag adds support for surfaces with a color-channel ordering different
    // from the API default. It is required for compatibility with Direct2D.
    UINT deviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED |
        D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG) || defined(_DEBUG)
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    //deviceFlags |= D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

    // Create the Direct3D 11 API device object and a corresponding context.
    Microsoft::WRL::ComPtr<ID3D11Device>        device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

    HRESULT hr = D3D11CreateDevice(
        nullptr,                    // Specify nullptr to use the default adapter.
        D3D_DRIVER_TYPE_HARDWARE,   // Create a device using the hardware graphics driver.
        0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
        deviceFlags,                // Set debug and Direct2D compatibility flags.
        levels,                     // List of feature levels this app can support.
        ARRAYSIZE(levels),          // Size of the list above.
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        &device,                    // Returns the Direct3D device created.
        &m_featureLevel,            // Returns feature level of device created.
        &context                    // Returns the device immediate context.
    );

    if (FAILED(hr))
    {
        // Handle device interface creation failure if it occurs.
        // For example, reduce the feature level requirement, or fail over 
        // to WARP rendering.
        return 0;
    }

    // Store pointers to the Direct3D 11.1 API device and immediate context.
    //device.As(&m_pd3dDevice);
    //context.As(&m_pd3dDeviceContext);

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Update the scene.
            //renderer->Update();

            // Render frames during idle time (when no messages are waiting).
            //renderer->Render();

            // Present the frame to the screen.
            //deviceResources->Present();
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_CREATE:
        return 0;

    case WM_SIZE:
        return 0;


    case WM_PAINT:
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
