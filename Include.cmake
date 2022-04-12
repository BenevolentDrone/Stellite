# This is like a library file for CMakeLists

#This function takes all cpp files in the folder specified with an argument (recursively) and add them to the list of all cpp files
# Argument: TARGET_DIRECTORY
function(include_sources TARGET_DIRECTORY)

    # Get the current list of cpp files from the property
    # Target variable: CURRENT_SOURCE_FILES
    # Scope: global
    # Property name: ALL_SOURCE_FILES
    get_property(
        CURRENT_SOURCE_FILES
        GLOBAL
        PROPERTY ALL_SOURCE_FILES)

    # Debug message
    #message(STATUS "Current source file list: ${CURRENT_SOURCE_FILES}")

    # Make the list of cpp files inside this particular CMake hierarchy
    # Target variable: LOCAL_SOURCE_FILES
    # CONFIGURE_DEPENDS - i dunno, they say that using GLOB and GLOB_RECURSE is shit because you have to do "cmake .."
    # (or CMake: Configure in VS Code) command every time you add or delete cpp files or the entire project may not compile
    # (https://stackoverflow.com/questions/3201154/automatically-add-all-files-in-a-folder-to-a-target-using-cmake)
    # (https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak/18538444#18538444)
    # This argument was introduced with some shiny new version of CMake; it makes compiling time longer but makes sure
    # something something is done automatically but still the CMake devs 'discourage' from using GLOB anyway; the 'true' way
    # being typing in ALL cpp file paths into CMakeLists files MANUALLY. Coming from C# any of these options look like 
    # time wasting shit to me. I mean seriously, instead of learning c++ by doing code I am busy googling:
    # - Some CMake language that I had no intent to learn;
    # - Which compiler to use and why would I need to be careful with optimization flags;
    # - The ways to resolve issues with the disfunctional linker that should be just ripped off the CLR and call it a day instead; 
    # - And finally which package manager to use because apparently the CPP people are too brutal to bath in the user friendliness
    # of NPM and NuGet
    # Argument: TARGET_DIRECTORY
    file(GLOB_RECURSE
        LOCAL_SOURCE_FILES
        CONFIGURE_DEPENDS
        "${TARGET_DIRECTORY}/*.cpp")
    
    # Append the current list with the latter list
    # Target variable: CURRENT_SOURCE_FILES
    # Argument: LOCAL_SOURCE_FILES
    list(APPEND
        CURRENT_SOURCE_FILES
        ${LOCAL_SOURCE_FILES})
    
    # Debug message
    #message(STATUS "New source file list: ${CURRENT_SOURCE_FILES}")
    
    # Set the property back with the concatenated list
    # Scope: gloval
    # Property name: ALL_SOURCE_FILES
    # Argument: CURRENT_SOURCE_FILES
    set_property(
        GLOBAL
        PROPERTY ALL_SOURCE_FILES
        ${CURRENT_SOURCE_FILES})
    
endfunction()