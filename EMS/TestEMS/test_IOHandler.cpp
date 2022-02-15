#include "pch.h"
#include "../EMS/IOHandler.h"

TEST(IOHandler테스트, parseInput테스트) {
	IOHandler io_handler;

	EXPECT_EQ(io_handler.parsetInput("ADD, , , , 18050301, KYUMOK KIM, CL2, 010 - 9777 - 6055, 19980906, PRO")[0], "ADD");
	EXPECT_EQ(io_handler.parsetInput("ADD, , , , 18050301, KYUMOK KIM, CL2, 010 - 9777 - 6055, 19980906, PRO")[1], "p");
}
