local myenemy = {}
local x = 0
local y = 0
function myenemy.onCreate(entity)
    print("making enemy")
    x, y = quee_script_get_pos(entity)
end
function myenemy.onUpdate(entity)
    y = y + 1
    quee_script_set_pos(entity, x, y)
end

return myenemy
