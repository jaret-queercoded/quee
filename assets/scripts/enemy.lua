local myenemy = {}
local x = 0
local y = 0
function myenemy.onCreate(entity)
    x, y = quee_script_get_pos(entity)
    print(player.health)
end
function myenemy.onUpdate(entity)
    y = y + 1
    quee_script_set_pos(entity, x, y)
end

return myenemy
