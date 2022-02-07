Player = {}
Player.__index = Player

function Player:create(health, x, y)
    local plyr = {}
    setmetatable(plyr, Player)
    plyr.health = health
    plyr.x = x
    plyr.y = y
    return plyr
end

_G.player = Player:create(100, 0.0, 0.0)
-- quee functions
function onCreate(entity)
    print('onCreate')
    player.x, player.y = quee_script_get_pos(entity)
end

function onUpdate(entity)
    player.x = player.x + 1
    print(player.x .. player.y)
    quee_script_set_pos(entity, player.x, player.y)
    print('Player Health: ' .. player.health)
end
