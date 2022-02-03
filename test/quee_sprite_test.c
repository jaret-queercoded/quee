#include "quee_sprite_test.h"

#include "../quee_sprite.h"
#include "../quee_texture.h"
#include "quee_test_helper.h"

quee_test_result test_quee_sprite_creation() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    quee_sprite *sprite = create_quee_sprite(quee_texture_manager_get(manager, "assets/test/test.png"));
    QUEE_ASSERT(sprite, "We didn't get a sprite back");
    QUEE_ASSERT(sprite->texture, "We should have a texture");
    QUEE_ASSERT(sprite->curr_frame == NULL, "Current frame should be null");
    QUEE_ASSERT(sprite->frames == NULL, "Frames should be null");
    QUEE_ASSERT(sprite->frame_index == 0, "Frame index should be 0");
    QUEE_ASSERT(sprite->max_frames == 0, "Max frames should be 0");
    QUEE_ASSERT(sprite->num_frames == 0, "Num frames should be 0");
    QUEE_ASSERT(sprite->ticks_on_frame == 0, "Ticks on frame should be 0");
    destroy_quee_sprite(&sprite);
    QUEE_ASSERT(sprite == NULL, "Sprite destroy left a dangling pointer");
    destroy_quee_texture_manager(&manager);
    return QUEE_PASSED;
}

quee_test_result test_quee_sprite_add_frame() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    quee_sprite *sprite = create_quee_sprite(quee_texture_manager_get(manager, "assets/test/test.png"));
    quee_sprite_init_frames(sprite, 2);
    QUEE_ASSERT(sprite->max_frames == 2, "Should have a max of two frames now!");
    QUEE_ASSERT(sprite->frame_index == 0, "Should have a frame index of 0");
    quee_frame frame1 = {.rect = {.x = 0, .y = 0, .w = 32, .h = 32}, .ticks = 100};
    quee_frame frame2 = {.rect = {.x = 0, .y = 0, .w = 32, .h = 32}, .ticks = 1000};
    quee_frame frame3 = {.rect = {.x = 0, .y = 0, .w = 32, .h = 32}, .ticks = 10000};
    QUEE_ASSERT(quee_sprite_add_frame(sprite, frame1) == 0, "We should have been able to add frame1");
    QUEE_ASSERT(sprite->num_frames == 1, "Should of had one frame");
    QUEE_ASSERT(quee_sprite_add_frame(sprite, frame2) == 0, "We should have been able to add frame2");
    QUEE_ASSERT(sprite->num_frames == 2, "Should of had two frames");
    QUEE_ASSERT(quee_sprite_add_frame(sprite, frame3) == -1, "We should have not been able to add frame3");
    QUEE_ASSERT(sprite->num_frames == 2, "Should of still had two frames");
    destroy_quee_sprite(&sprite);
    destroy_quee_texture_manager(&manager);
    return QUEE_PASSED;
}

quee_test_result test_quee_sprite_update() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    quee_sprite *sprite = create_quee_sprite(quee_texture_manager_get(manager, "assets/test/test.png"));
    quee_sprite_init_frames(sprite, 2);
    QUEE_ASSERT(sprite->max_frames == 2, "Should have a max of two frames now!");
    QUEE_ASSERT(sprite->frame_index == 0, "Should have a frame index of 0");
    quee_frame frame1 = {.rect = {.x = 0, .y = 0, .w = 32, .h = 32}, .ticks = 100};
    quee_frame frame2 = {.rect = {.x = 0, .y = 0, .w = 32, .h = 32}, .ticks = 1000};
    quee_sprite_add_frame(sprite, frame1);
    quee_sprite_add_frame(sprite, frame2);
    quee_frame *f_ptr = sprite->curr_frame;
    update_quee_sprite(sprite, 90);
    QUEE_ASSERT(f_ptr == sprite->curr_frame, "We should still be on the first frame");
    update_quee_sprite(sprite, 10);
    QUEE_ASSERT(f_ptr != sprite->curr_frame, "We should be on the second frame");
    update_quee_sprite(sprite, 1000);
    QUEE_ASSERT(f_ptr == sprite->curr_frame, "We should be back on the first frame");
    destroy_quee_sprite(&sprite);
    destroy_quee_texture_manager(&manager);
    return QUEE_PASSED;
}
