#include "ApplicationRunner.h"

void runApplicationTestSuite(char *applicationPath, char *resourcesPath);
void runApplicationTestSuite(char *applicationPath, char *resourcesPath) {
  TestEnvironment testEnvironment = (TestEnvironment)malloc(sizeof(TestEnvironmentMembers));
  testEnvironment->applicationPath = applicationPath;
  testEnvironment->resourcesPath = resourcesPath;
  testEnvironment->results = newTestSuite("Application", NULL, NULL);

  runApplicationTest(testEnvironment, "Run with no plugins",
    "",
    RETURN_CODE_INVALID_PLUGIN_CHAIN, false);
  runApplicationTest(testEnvironment, "List plugins",
    "--list-plugins",
    RETURN_CODE_NOT_RUN, false);
  runApplicationTest(testEnvironment, "Process with again plugin",
    "--plugin again",
    RETURN_CODE_SUCCESS, true);

  free(testEnvironment->results);
  free(testEnvironment);
}
