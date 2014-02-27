
struct ApplicationData
{
	ApplicationData(WindowWin32 *window_ptr, GraphicsDevice *graphics_ptr) :
		window(*window_ptr),
		graphics(*graphics_ptr)
	{

	}
	WindowWin32 &window;
	GraphicsDevice &graphics;
};

enum MouseState
{
	MouseNone,
	//Mouse
};

class ApplicationCallback
{
public:
	virtual void init(ApplicationData &app) = 0;
	virtual void render(ApplicationData &app) = 0;
	virtual void keyDown(ApplicationData &app, UINT key) = 0;
	virtual void keyPressed(ApplicationData &app, UINT key) = 0;
	virtual void mouse(ApplicationData &app, int x, int y, int prevX, int prevY) = 0;
};

class ApplicationWin32
{
public:
	ApplicationWin32(HINSTANCE instance, UINT windowWidth, UINT windowHeight, const std::string &name, GraphicsDeviceType graphicsType, ApplicationCallback &callback);
	~ApplicationWin32();

	void messageLoop();

	inline ApplicationData& data()
	{
		return *m_data;
	}
	inline ApplicationCallback& callback()
	{
		return m_callback;
	}

private:
	//
	// m_data is just a view to encapsulate all externally-visible application
	// components. THe actual data is owned by m_window, m_device, etc.
	//
	ApplicationData *m_data;
	
	WindowWin32 m_window;
	GraphicsDevice *m_graphics;

	HINSTANCE m_instance;

	ApplicationCallback &m_callback;
};
