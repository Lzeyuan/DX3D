#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		uint8_t code;

	public:
		Event() noexcept
			:
			type(Type::Invalid),
			code(0u)
		{}
		Event(Type type, uint8_t code) noexcept
			:
			type(Type::Invalid),
			code(code)
		{}
		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}
		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}
		bool IsValid() const noexcept
		{
			return type == Type::Invalid;
		}
		uint8_t GetCode() const noexcept
		{
			return code;
		}
	};
public:
	// 新建类：析构函数、构造函数、拷贝构造、拷贝赋值、后两者的move语义
	// 要么一起出现，要么都不出现
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard(const Keyboard&&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&&) = delete;
	~Keyboard() = default;

	// key envent stuff
	bool KeyIsPress(uint8_t keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;
	// char event stuff
	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;
	// autorepeat control
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;
private:
	void OnKeyPressed(uint8_t keycode) noexcept;
	void OnKeyReleased(uint8_t keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TimerBuffer(std::queue<T>& buffer) noexcept;
private:
	// MSDN上的虚拟按键代码是16位的
	static constexpr uint16_t nKeys = 256u;
	// 键盘事件队列人为设置上限16
	static constexpr uint32_t bufferSize = 16u;
	bool autorepeatEnable = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};