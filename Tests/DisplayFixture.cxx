///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "LoggerMock.h"
#include "gmock/gmock.h"
#include "BitmapMock.hxx"
#include "DisplayFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MATCHER_P (AreRectsEq, v_rect, "Expects rects match")
{
    return (arg.Dimension.Width  == v_rect.Dimension.Width ) &&
           (arg.Dimension.Height == v_rect.Dimension.Height) &&
           (arg.Coordinate.X     == v_rect.Coordinate.X    ) &&
           (arg.Coordinate.Y     == v_rect.Coordinate.Y    );
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AtLeast;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (DisplayFixture, CheckTheBitmapValidationOutsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationOutsideTheScreen");

    LOGI (MODULE, "The bitmap will exceed the width of the screen");
    EXPECT_CALL (DisplayMock, validate (_)).WillOnce (Invoke (&DisplayMock, &DisplayMock::Validate))
                                           .WillOnce (Invoke (&DisplayMock, &DisplayMock::Validate));

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ONE;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_FALSE (DisplayMock.DrawBitmap (BitmapMock));

    LOGI (MODULE, "The bitmap will exceed the height of the screen");
    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ONE;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_FALSE (DisplayMock.DrawBitmap (BitmapMock));
}

TEST_F (DisplayFixture, CheckTheBitmapValidationInsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationInsideTheScreen");

    LOGI (MODULE, "Full-screen bitmap");
    EXPECT_CALL (DisplayMock, validate  (_)).WillOnce (Invoke (&DisplayMock, &DisplayMock::Validate))
                                            .WillOnce (Invoke (&DisplayMock, &DisplayMock::Validate));
    EXPECT_CALL (DisplayMock, sendLines (_)).Times    (AtLeast (ZERO));

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_TRUE (DisplayMock.DrawBitmap (BitmapMock));
    
    LOGI (MODULE, "A bitmap on the screen");
    BitmapMock.Coordinate.X     = FORTY;
    BitmapMock.Coordinate.Y     = FIFTY;
    BitmapMock.Dimension.Width  = ONE_HUNDRED;
    BitmapMock.Dimension.Height = ONE_HUNDRED;
    ASSERT_TRUE (DisplayMock.DrawBitmap (BitmapMock));
}

TEST_F (DisplayFixture, CheckTheAmountOfDataSentToTheDisplayForTheFullScreenBitmap)
{
    LOGW (MODULE, "CheckTheAmountOfDataSentToTheDisplay");

    EXPECT_CALL (DisplayMock, validate  (_)).WillOnce (Return (true));
    EXPECT_CALL (DisplayMock, sendLines (_)).Times    (SIXTEEN);

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_TRUE (DisplayMock.DrawBitmap (BitmapMock));
}

TEST_F (DisplayFixture, CheckTheAmountOfDataSentToTheDisplayForTheSmallBitmap)
{
    LOGW (MODULE, "CheckTheAmountOfDataSentToTheDisplayForTheSmallBitmap");

    EXPECT_CALL (DisplayMock, validate  (_)).WillOnce (Return (true));
    EXPECT_CALL (DisplayMock, sendLines (_)).Times    (ONE);

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = FIVE;
    BitmapMock.Dimension.Height = FIVE;
    ASSERT_TRUE (DisplayMock.DrawBitmap (BitmapMock));
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////