set_xmakever("3.0.0")

target("emdevif_test_framework", function ()
    set_kind("static")
    add_files("src/*.c")
    add_includedirs("inc/", {public = true})
end)

option("EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST", {default = false, description = "Enabled it to enable test"})

includes("test")
