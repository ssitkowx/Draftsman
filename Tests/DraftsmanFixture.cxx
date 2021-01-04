///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "LoggerMock.h"
#include "gmock/gmock.h"
#include "BitmapMock.hxx"
#include "DraftsmanFixture.hxx"

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

TEST_F (DraftsmanFixture, CheckTheBitmapValidationOutsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationOutsideTheScreen");

    LOGI (MODULE, "The bitmap will exceed the width of the screen");
    EXPECT_CALL (DraftsmanMock, validate (_)).WillOnce (Invoke (&DraftsmanMock, &DraftsmanMock::Validate))
                                           .WillOnce (Invoke (&DraftsmanMock, &DraftsmanMock::Validate));

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ONE;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_FALSE (DraftsmanMock.DrawBitmap (BitmapMock));

    LOGI (MODULE, "The bitmap will exceed the height of the screen");
    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ONE;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_FALSE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheBitmapValidationInsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationInsideTheScreen");

    LOGI (MODULE, "Full-screen bitmap");
    EXPECT_CALL (DraftsmanMock, validate  (_)).WillOnce (Invoke (&DraftsmanMock, &DraftsmanMock::Validate))
                                              .WillOnce (Invoke (&DraftsmanMock, &DraftsmanMock::Validate));
    EXPECT_CALL (DraftsmanMock, sendLines (_)).Times    (AtLeast (ZERO));

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
    
    LOGI (MODULE, "A bitmap on the screen");
    BitmapMock.Coordinate.X     = FORTY;
    BitmapMock.Coordinate.Y     = FIFTY;
    BitmapMock.Dimension.Width  = ONE_HUNDRED;
    BitmapMock.Dimension.Height = ONE_HUNDRED;
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheAmountOfDataSentToTheDisplayForTheFullScreenBitmap)
{
    LOGW (MODULE, "CheckTheAmountOfDataSentToTheDisplay");

    EXPECT_CALL (DraftsmanMock, validate  (_)).WillOnce (Return (true));
    EXPECT_CALL (DraftsmanMock, sendLines (_)).Times    (SIXTEEN);

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = THREE_HUNDRED_NINETEEN;
    BitmapMock.Dimension.Height = TWO_HUNDRED_THIRTY_NINE;
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheAmountOfDataSentToTheDisplayForTheSmallBitmap)
{
    LOGW (MODULE, "CheckTheAmountOfDataSentToTheDisplayForTheSmallBitmap");

    EXPECT_CALL (DraftsmanMock, validate  (_)).WillOnce (Return (true));
    EXPECT_CALL (DraftsmanMock, sendLines (_)).Times    (ONE);

    BitmapMock.Id               = ZERO;
    BitmapMock.Coordinate.X     = ZERO;
    BitmapMock.Coordinate.Y     = ZERO;
    BitmapMock.Dimension.Width  = FIVE;
    BitmapMock.Dimension.Height = FIVE;
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////