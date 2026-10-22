add_rules("mode.release", "mode.debug")
set_languages("gnu17")

target("main")
    set_kind("binary")
    set_default(true)
    add_deps("string")
    add_files("src/main.c")

target("string")
    set_kind("object")
    add_files("src/string.c")

-- for test
target("test_lib")
    set_kind("object")
    set_default(false)
    add_files("src/tests_lib.c")

for _, file in ipairs(os.files("src/test_*.c")) do
    local name = path.basename(file)
    target("test")
        set_kind("binary")
        set_default(false)
        add_files("src/"..name..".c")
        add_deps("string", "test_lib")
        add_tests("test", {realtime_output = true, remove_files = "src/main.c"})
end
