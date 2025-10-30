set_xmakever("3.0.4")

option("EMDEVIF_TEST_FRAMEWORK_TEST_NAME", {description = "Select which test to run."})

target("emdevif_test_framework_test", function ()
    set_kind("phony")
    set_default(false)

    on_build(function (target) 
        if (has_config("EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST")) then
            os.cd("$(scriptdir)/..")
            os.mkdir("$(builddir)/emdevif_xmake_test_out")

            import("core.project.config")
            local test_name = config.get("EMDEVIF_TEST_FRAMEWORK_TEST_NAME")
            local generator = config.get("trybuild") or ""

            if (generator ~= "") then
                local XMAKE_GENERATOR_TO_CMAKE = {
                    make      = "Unix Makefiles",
                    ninja     = "Ninja",
                    vs2022    = "Visual Studio 17 2022",
                    vs2019    = "Visual Studio 16 2019",
                    vs2017    = "Visual Studio 15 2017",
                    vs2015    = "Visual Studio 14 2015",
                    vs2013    = "Visual Studio 12 2013",
                    vs2012    = "Visual Studio 11 2012",
                    vs2010    = "Visual Studio 10 2010",
                    vs2008    = "Visual Studio 9 2008",
                    mingw     = "MinGW Makefiles",
                    msys      = "MSYS Makefiles",
                    cygwin    = "Unix Makefiles"
                }
                generator = XMAKE_GENERATOR_TO_CMAKE[generator]
                generator = " -G " .. generator
            end

            os.exec("cmake -S ." .. generator .. " "
                .. " -DEMDEVIF_TEST_FRAMEWORK_ENABLE_TEST=ON "
                .. "-DEMDEVIF_TEST_FRAMEWORK_TEST_NAME=" .. test_name .. " "
                .. "-B $(builddir)/emdevif_xmake_test_out"
            )
            os.exec("cmake --build $(builddir)/emdevif_xmake_test_out")
        else
            os.raise("The value of EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST was undefined, please set it.")
        end
    end)

    on_run(function (target)
        os.cd("$(builddir)/emdevif_xmake_test_out")
        os.execv("ctest", {"."})
    end)

    on_clean(function (target) 
        os.rm("$(builddir)/emdevif_xmake_test_out")
    end)
end)
