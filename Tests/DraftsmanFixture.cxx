///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "BitmapHw.h"
#include "LoggerHw.h"
#include "gmock/gmock.h"
#include "DraftsmanFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

using ::testing::_;
using ::testing::Invoke;
using ::testing::AtLeast;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (DraftsmanFixture, CheckTheBitmapValidationOutsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationOutsideTheScreen");

    LOGI (MODULE, "The bitmap will exceed the width of the screen");
    BitmapHw.Id         = ZERO;
    BitmapHw.Coordinate = { ONE                 , ZERO              };    // X, Y
    BitmapHw.Dimension  = { THREE_HUNDRED_TWENTY, TWO_HUNDRED_FORTY };    // Width, Height
    ASSERT_FALSE (DraftsmanHw.DrawBitmap (BitmapHw));

    LOGI (MODULE, "The bitmap will exceed the height of the screen");
    BitmapHw.Id         = ZERO;
    BitmapHw.Coordinate = { ZERO                , ONE               };    // X, Y
    BitmapHw.Dimension  = { THREE_HUNDRED_TWENTY, TWO_HUNDRED_FORTY };    // Width, Height
    ASSERT_FALSE (DraftsmanHw.DrawBitmap (BitmapHw));
}

TEST_F (DraftsmanFixture, CheckTheBitmapValidationInsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationInsideTheScreen");

    LOGI        (MODULE, "Full-screen bitmap");
    EXPECT_CALL (DraftsmanHw, sendLines (_)).Times (AtLeast (ONE));

    BitmapHw.Id         = ZERO;
    BitmapHw.Coordinate = { ZERO             , ZERO                 };    // X, Y
    BitmapHw.Dimension  = { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY };    // Width, Height
    ASSERT_TRUE (DraftsmanHw.DrawBitmap (BitmapHw));
    
    LOGI (MODULE, "A bitmap on the screen");
    BitmapHw.Id         = ZERO;
    BitmapHw.Coordinate = { FORTY               , FIFTY             };    // X, Y
    BitmapHw.Dimension  = { ONE_HUNDRED         , ONE_HUNDRED       };    // Width, Height
    ASSERT_TRUE (DraftsmanHw.DrawBitmap (BitmapHw));
}

TEST_F (DraftsmanFixture, CheckTheSizeOfDataSentToTheDisplayForTheFullScreenBitmap)
{
    LOGW (MODULE, "CheckTheSizeOfDataSentToTheDisplay");

    EXPECT_CALL (DraftsmanHw, sendLines (_)).Times (TWENTY_TWO);

    BitmapHw.Id         = ZERO;
    BitmapHw.Coordinate = { ZERO             , ZERO                 };    // X, Y
    BitmapHw.Dimension  = { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY };    // Width, Height
    ASSERT_TRUE (DraftsmanHw.DrawBitmap (BitmapHw));
}

TEST_F (DraftsmanFixture, CheckTheSizeOfDataSentToTheDisplayForTheSmallBitmap)
{
    LOGW (MODULE, "CheckTheSizeOfDataSentToTheDisplayForTheSmallBitmap");

    EXPECT_CALL (DraftsmanHw, sendLines (_)).Times (ONE);

    BitmapHw.Id         = ZERO;
    BitmapHw.Coordinate = { ZERO, ZERO };                                 // X, Y
    BitmapHw.Dimension  = { FIVE, FIVE };                                 // Width, Height
    ASSERT_TRUE (DraftsmanHw.DrawBitmap (BitmapHw));
}

TEST_F (DraftsmanFixture, CheckTheNumberOfChunksSentToTheDisplay)
{
    LOGW    (MODULE, "CheckTheNumberOfChunksSentToTheDisplay");

    ON_CALL (DraftsmanHw, calculate (_)).WillByDefault (Invoke (&DraftsmanHw, &DraftsmanHw::Calculate));

    uint8_t dataChunksLen = ONE;
    for (const auto & calc : CalculationsMatcher)
    {
        Bitmap bitmap;
        bitmap.Dimension = { calc.second.first, calc.second.second };
        ASSERT_EQ (DraftsmanHw.Calculate (bitmap.Dimension), dataChunksLen++);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////