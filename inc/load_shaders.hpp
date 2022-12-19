#pragma once

#include <GL/glew.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
