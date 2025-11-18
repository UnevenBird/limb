R"luastring"--(

local print = print
local limb = require('limb')
limb.log = function(...) -- tmp logging function
	local args = {}
	local i = 1
	for _,v in ipairs({...}) do
		if v then
			args[i] = tostring(v)
			i=i+1
		end
	end
	print(table.concat(args, " "))
end

function limb.boot()
	limb.log("LIMB", string.format("v%d.%d", limb.getVersion()))
	limb.log("OS: ", limb.getOS())

	-- require modules
	for k,v in ipairs {
		"window",
		"timer",
		"event",
		"graphics",
	} do
		limb[v] = require("limb." .. v)
	end

	limb.window.create('Untitled', 1280, 720)
	limb.timer.create()
end

function limb.run()
	if limb.load then limb.load() end

	limb.graphics.setBackgroundColor(0x212121)
	limb.timer.step()

	return function()
		limb.event.pump()
		for name, a,b,c,d,e,f in limb.event.poll() do
			limb.log(name, a,b,c,d,e,f)
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
