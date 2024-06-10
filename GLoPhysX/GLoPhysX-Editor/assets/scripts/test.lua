function OnCreate()
    print("Lua OnCreate called")
end

function OnUpdate(deltaTime)
    print("Lua OnUpdate called with deltaTime: " .. deltaTime)
end

function OnDestroy()
    print("Lua OnDestroy called")
end