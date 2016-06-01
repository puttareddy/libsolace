
set(TEST_SOURCE_FILES
        main.cpp
        ci/teamcity_messages.cpp
        ci/teamcity_cppunit.cpp
        test_byteBuffer.cpp
        test_optional.cpp
        test_uuid.cpp
        test_char.cpp
        test_array.cpp
        test_string.cpp
        test_stringBuilder.cpp
        test_path.cpp
        test_version.cpp
         )

add_executable(test_${PROJECT_NAME} ${TEST_SOURCE_FILES})
target_link_libraries(test_solace cppunit solace fmt)