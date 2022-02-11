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

function player_module.onUpdate(entity)
    local delta_time = quee_script_get_delta_time(entity)
    player.x = player.x + (move_speed * delta_time)
    player.y = player.y + (move_speed * delta_time)
    quee_script_set_pos(entity, player.x, player.y)
end

return player_module
