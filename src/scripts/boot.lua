R"luastring"--(

local limb = require("limb")

function limb.boot()
	limb.logf("LIMB v{}.{}", limb.getVersion())
	limb.logf("OS: {}", limb.getOS())

	-- require modules
	for _,v in ipairs {
		"window",
		"timer",
		"event",
		"graphics",
		"filesystem",
	} do
		limb[v] = require("limb." .. v)
		limb.logf("required module {}", v)
	end

	-- default app configuration
	local c = {
		entrypoint = "main.lua",
		window = {
			title = "Untitled",
			width = 1280,
			height = 720,
		}
	}

	local conf_path = "conf.lua"
	if limb.filesystem.exists(conf_path) then
		require(limb.filesystem.removeExtension(conf_path))
		limb.conf(c)
	end

	limb.window.create(c.window.title, c.window.width, c.window.height)
	limb.timer.create()

	local entrypoint_found = limb.filesystem.exists(c.entrypoint)
	limb.logf("entry point '{}': {}", c.entrypoint, entrypoint_found and "found" or "not found")
	if entrypoint_found then
		require(limb.filesystem.removeExtension(c.entrypoint))
	end
end

function limb.run()
	if limb.load then limb.load() end

	limb.graphics.setBackgroundColor(0x212121)
	limb.timer.step()

	return function()
		limb.event.pump()
		for name, a,b,c,d,e,f in limb.event.poll() do
			if name == "quit" then
				return 1
			end
		end

		local dt = limb.timer.step()
		if limb.update then limb.update(dt) end

		limb.graphics.clear()
		if limb.render then limb.render() end
		limb.graphics.present()
	end
end

local xpcall = xpcall
local coroutine_yield = coroutine.yield
local debug, tostring = debug, tostring

local function error_logger(msg, layer)
	limb.log((debug.traceback("Error: " .. tostring(msg), 1+(layer or 1)):gsub("\n[^\n]+$", "")))
end

return function()
	local boot_success = xpcall(limb.boot, error_logger)
	if not boot_success then return 1 end

	local run_success, main_loop = xpcall(limb.run, error_logger)
	if not run_success then return 1 end

	while true do
		local success, retval = xpcall(main_loop, error_logger)
		if not success then retval = 1 end
		if retval then return retval end
		coroutine_yield()
	end

	return 1
end

--)luastring"--"
