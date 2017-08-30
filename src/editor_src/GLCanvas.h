#ifndef WX_GL_CANVAS_H
#define WX_GL_CANVAS_H
#include "../TextureManager.h"
#include <wx/wx.h>
#include "../GLDevice.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../DefaultShader.h"
#include "../GameCamera.h"
#include "../SpriteBatcher.h"
#include "../LightStruct.h"
#include "../LightShader.h"
#include "../typedefs.h"
#include "../Level.h"
#include <wx/glcanvas.h>
#include "../EntityManager.h"
#include "../Player.h"

/*
 * I'm this is going to render the game scene.
 * to paint the scene I'm probably going to store the game data
 * and render the data when it's sent.
 *
 * I really do want to follow the single responsibility for each class ideal
 * but it seems to be very hard to work with in wxWidgets. but then again this is the
 * second wxWidgets application I've created other than a calculator
 */
#include <memory>
const int SELECT_M=0;
const int DELETE_M=1;
const int CREATE_M=2;
class GLCanvas : public wxGLCanvas{
	public:
		GLCanvas( wxWindow* parent, const wxGLAttributes& disp, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0 );
		~GLCanvas(){}
		void PaintScene( wxPaintEvent& pnt );	
		void OnResize ( wxSizeEvent& evnt );
		void MouseEvents( wxMouseEvent& ev );
		void KeyboardEvents( wxKeyEvent& ev );

		void LogicRefresh();
		
		void SetTextureManagerPtr( const std::shared_ptr<TextureManager>& tm ) { this->tm = tm; }

		const std::shared_ptr<IDevice>& get_device() { return dev; }
		Level& get_level() { return current; }
		GameCamera& get_camera() { return camera; }
		Player& get_player() { return player; }
		// the syntax for this is weird.
		Entity*& get_current() { return currentEnt; }
		bool& lighting_enabled() { return lighting; }
		bool& parallax_enabled() { return parallax; }
		void save();
		void save(std::string path);
		void copy_f();
		void paste();
		void delete_cur();
		int &get_mode(){ return mode; }
		bool should_update=false;
	private:
		glm::mat4 view=glm::mat4();
		glm::mat4 projection;		
	private:
		int mode=0;
		bool lighting=false;
		bool parallax=false;
		GameCamera camera;
		Level current;
		Player player;
		// I'm going to use a pointer to the current entity to figure anything out.
		Entity* currentEnt = nullptr;
		// used for my little copy and paste system :D
		Entity* copy = nullptr;
		EntityManager entity_manager;
		std::array<Light, 10> lights;
		wxGLContext* ctx_obj;
		std::shared_ptr<DefaultShader> ds;
		std::shared_ptr<LightShader> ls;
		std::shared_ptr<SpriteBatcher> sb;
		std::shared_ptr<TextureManager> tm;
		std::shared_ptr<IDevice> dev;
		wxSize viewPort_sz;
		DECLARE_EVENT_TABLE()
};

#endif
