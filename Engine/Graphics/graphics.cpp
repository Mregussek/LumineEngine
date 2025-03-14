
module;

#include "GLogger.h"

module Graphics;

namespace lumine
{

void GraphicsClass::hello()
{
	GCREATE_LOGGER();
	GTRACE("Hello from Graphics Logger!");
	GDEBUG("Hello from Graphics Logger!");
	GINFO("Hello from Graphics Logger!");
	GWARN("Hello from Graphics Logger!");
	GERROR("Hello from Graphics Logger!");
	GCRITICAL("Hello from Graphics Logger!");
}

}
