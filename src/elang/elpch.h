#include <assert.h>

#include <string>
#include <cstring>
#include <algorithm>
#include <type_traits>

#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <chrono>
#include <random>
#include <cmath>
#include <limits>
#include <functional>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifdef _WIN32
#include "windows.h"
#endif

#pragma warning( push )
#pragma warning( disable : 26495 )
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( push )
#pragma warning( disable : 4334 )
#pragma warning( push )
#pragma warning( disable : 26819 )
#pragma warning( push )
#pragma warning( disable : 26415 )
#ifdef ELANG_SDL
#include <SDL2/SDL.h>
#endif
#include <GL/glew.h>
#include <tsl/robin_map.h>
#include <tsl/robin_set.h>
#include <entt/entt.hpp>
////#include <cereal/archives/binary.hpp>
////#include <cereal/types/utility.hpp>
////#include <cereal/types/string.hpp>
////#include <cereal/types/vector.hpp>
////#include <cereal/types/map.hpp>
////#include <cereal/types/unordered_map.hpp>
////#include <cereal/types/array.hpp>
////#include <cereal/types/list.hpp>
////#include <cereal/types/common.hpp>
////#include <encoder/fpng.h>
////#include <lodepng/lodepng.h>
////#include <tweeny/tweeny.h>
#pragma warning( pop )
#pragma warning( pop )
#pragma warning( pop )
#pragma warning( pop )
#pragma warning( pop )
//
#include "common/define.h"
#include "common/string.h"
#include "common/vector.h"
#include "common/fileio.h"
#include "common/batch.h"
#include "common/vec2.h"
#include "common/vec3.h"
#include "common/vec4.h"
#include "common/vertex.h"
#include "registry/registry.h"
#include "tools/controls.h"
#include "tools/hashmap.h"

#ifdef ELANG_GUI
#include <QtCore/qglobal.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QDir>
#include <QtWidgets/QWidget>
#include <QtOpenGLWidgets/QOpenGlWidget>
#include <QtGui/qopenglcontext.h>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QLineEdit>
#include <QtGui/QCloseEvent>
#include <QtGui/QAction>
#include <QtGui/QActiongroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QTimer>
#include <QtGui/QImage>
#endif