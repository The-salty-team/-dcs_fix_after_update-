package.path = package.path ..';./Scripts/DemoScenes/?.lua;'
local sceneEnvironment = require("demosceneEnvironment")

scene = {} -- сюда кладем все созданные объекты

function loadScene(scenePtr)
    sceneAPI = sceneEnvironment.getInterface(scenePtr)
    sceneAPI:setUpdateFunc('sceneVRUpdate')
    sceneAPI:setSun(math.rad(-90), math.rad(0)) -- ?????? ?????? ?? ???????? ???? ?? ???????

        local cam_level = 1.8

    scene.cam        = sceneAPI:addCamera(3, cam_level , 3)
    scene.cam:setFarClip(1000.0)
    scene.cam:setFov(90)
    scene.cam.transform:lookAtPoint(-10.0, cam_level, 0);
    scene.cam:setActive()
end

--[0;1]
local function pingpong(length, t)
    local tt = (t%length)*2/length
    if tt>1 then tt = 2-tt end
    return tt
end


function sceneVRUpdate(t, dt)

end



