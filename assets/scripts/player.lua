local player_module = {}
Player = {}
Player.__index = Player

local move_speed = 100.0

function Player:create(health)
    local plyr = {}
    setmetatable(plyr, Player)
    plyr.health = health
    plyr.x = 0.0
    plyr.y = 0.0
    return plyr
end

player = Player:create(100)
-- quee functions
function player_module.onCreate(entity)
    player.x, player.y = quee_script_get_pos(entity)
end

function player_module.onCollision(entity, collision)
    print(quee_script_get_name(collision))
end

function player_module.onUpdate(entity)
    local delta_time = quee_script_get_delta_time(entity)
    if quee_script_is_key_held('w') then
        player.y = player.y - (move_speed * delta_time)
    end
    if quee_script_was_key_released('w') then
        quee_script_play_sound()
        print('w was released')
    end
    if quee_script_is_key_held('s') then
        player.y = player.y + (move_speed * delta_time)
    end
    if quee_script_is_key_held('a') then
        player.x = player.x - (move_speed * delta_time)
    end
    if quee_script_is_key_held('d') then
        player.x = player.x + (move_speed * delta_time)
    end
    if quee_script_is_key_pressed('left shift') or quee_script_is_key_pressed('right shift') then
        print('shfit pressed')
    end
    if quee_script_is_key_pressed('return') then
        print('pressed return')
    end
    quee_script_set_pos(entity, player.x, player.y)
end

return player_module
