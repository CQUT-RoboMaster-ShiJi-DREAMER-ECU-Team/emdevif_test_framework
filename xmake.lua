set_xmakever("3.0.4")

target("emdevif_test_framework", {kind = "static"}, function ()
    add_files("src/*.c")
    add_includedirs("inc/")
end)

option("EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST", {default = false, description = "Enabled it to enable test"})

includes("test")
