add_rules("mode.release", "mode.debug")
set_languages("gnu17")

includes("@builtin/xpack")

-- project metadata
set_project("ez-string")
set_version("0.0.1")
set_license("MIT")

target("main")
    set_kind("binary")
    set_default(true)
    add_files("src/main.c")

target("string")
    set_kind("object")
    add_files("src/ez-string.c")

-- for test
target("test-lib")
    set_kind("object")
    set_default(false)
    add_files("src/test/test-lib.c")

for _, file in ipairs(os.files("src/test/*.c")) do
    local name = path.basename(file)
    if name ~= "test-lib" then
        target(name, function()
            set_kind("binary")
            set_default(false)
            add_includedirs("src")
            add_files("src/test/"..name..".c")
            add_deps("string", "test-lib")
            add_tests("test", {realtime_output = true})
        end)
    end
end
