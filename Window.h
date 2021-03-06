#pragma once
#include "ExcludeMacro.h"
#include "WindowException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <optional>	// cpp 17

class Window
{
public:
	class Exception : public WindowException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	// ????ģʽ
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass(const WindowClass&&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&&) = delete;
		static constexpr const char* wndClassName = "DX11 3D Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	// BIG 5
	Window(int width, int height, const char* name);
	Window(const Window&) = delete;
	Window(const Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(const Window&&) = delete;
	~Window();

	// stuff
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
};

// error exception helper macro
#define CHWND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define CHWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())