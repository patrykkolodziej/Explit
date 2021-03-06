#pragma once

#include "../../math/Vector.hpp"
#include "../../math/QAngle.hpp"

typedef unsigned short client_shadow_handle_t;
typedef unsigned short client_render_handle_t;
typedef unsigned short model_instance_handle_t;
typedef unsigned char uint8_t;

class matrix3x4_t;
class i_client_unknown;
struct model_t;

class i_client_renderable
{
public:
	virtual i_client_unknown*          get_i_client_unknown() = 0;
	virtual Vector const&              get_render_origin(void) = 0;
	virtual QAngle const&              get_render_angles(void) = 0;
	virtual bool                       should_draw(void) = 0;
	virtual int                        get_render_flags(void) = 0; // erenderflags_xxx
	virtual void                       un_used(void) const {}
	virtual client_shadow_handle_t     get_shadow_handle() const = 0;
	virtual client_render_handle_t&    render_handle() = 0;
	virtual const model_t*             get_model() const = 0;
	virtual int                        draw_model(int flags, const int /*renderableinstance_t*/ &instance) = 0;
	virtual int                        get_body() = 0;
	virtual void                       get_color_modulation(float* color) = 0;
	virtual bool                       lod_test() = 0;
	virtual bool                       setup_bones(matrix3x4_t *pbonetoworldout, int nmaxbones, int bonemask, float currenttime) = 0;
	virtual void                       setup_weights(const matrix3x4_t *pbonetoworld, int nflexweightcount, float *pflexweights, float *pflexdelayedweights) = 0;
	virtual void                       do_animation_events(void) = 0;
	virtual void* /*ipvsnotify*/       get_pvs_notify_interface() = 0;
	virtual void                       get_render_bounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       get_render_bounds_world_space(Vector& mins, Vector& maxs) = 0;
	virtual void                       get_shadow_render_bounds(Vector &mins, Vector &maxs, int /*shadowtype_t*/ shadowtype) = 0;
	virtual bool                       should_receive_projected_textures(int flags) = 0;
	virtual bool                       get_shadow_cast_distance(float *pdist, int /*shadowtype_t*/ shadowtype) const = 0;
	virtual bool                       get_shadow_cast_direction(Vector *pdirection, int /*shadowtype_t*/ shadowtype) const = 0;
	virtual bool                       is_shadow_dirty() = 0;
	virtual void                       mark_shadow_dirty(bool bdirty) = 0;
	virtual i_client_renderable*       get_shadow_parent() = 0;
	virtual i_client_renderable*       first_shadow_child() = 0;
	virtual i_client_renderable*       next_shadow_peer() = 0;
	virtual int /*shadowtype_t*/       shadow_cast_type() = 0;
	virtual void                       create_model_instance() = 0;
	virtual model_instance_handle_t    get_model_instance() = 0;
	virtual const matrix3x4_t&         renderable_to_world_transform() = 0;
	virtual int                        look_up_attachment(const char *pattachmentname) = 0;
	virtual   bool                     get_attachment(int number, Vector &origin, QAngle &angles) = 0;
	virtual bool                       get_attachment(int number, matrix3x4_t &matrix) = 0;
	virtual float*                     get_render_clip_plane(void) = 0;
	virtual int                        get_skin() = 0;
	virtual void                       on_threaded_draw_setup() = 0;
	virtual bool                       uses_flex_delayed_weights() = 0;
	virtual void                       record_tool_message() = 0;
	virtual bool                       should_draw_for_splitscreen_user(int nslot) = 0;
	virtual uint8_t                    override_alpha_modulation(uint8_t nalpha) = 0;
	virtual uint8_t                    override_shadow_alpha_modulation(uint8_t nalpha) = 0;
};