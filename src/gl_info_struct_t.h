#ifndef GL_INFO_STRUCT_T_H
#define GL_INFO_STRUCT_T_H

#define ES_CONTEXT SDL_GL_CONTEXT_PROFILE_ES
#define COMPATIBILITY_CONTEXT SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
#define CORE_CONTEXT SDL_GL_CONTEXT_PROFILE_CORE
	struct gl_info_struct_t{
		int major;
		int minor;
		int depth;
		int stencil;
		int r_s;
		int g_s;
		int b_s;
		int a_s;
		bool double_buffer;
		bool force_accelerated;
		int context_type;
	};
#endif
