///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.hpp"
#include "Bitmap.hpp"
#include "LoggerHw.hpp"
#include <gmock/gmock.h>
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
    Bitmap.Id         = ZERO;
    Bitmap.Coordinate = { ONE                 , ZERO              };    // X, Y
    Bitmap.Dimension  = { THREE_HUNDRED_TWENTY, TWO_HUNDRED_FORTY };    // Width, Height
    ASSERT_FALSE (oDraftsmanHw.DrawBitmap (Bitmap));

    LOGI (MODULE, "The bitmap will exceed the height of the screen");
    Bitmap.Id         = ZERO;
    Bitmap.Coordinate = { ZERO                , ONE               };    // X, Y
    Bitmap.Dimension  = { THREE_HUNDRED_TWENTY, TWO_HUNDRED_FORTY };    // Width, Height
    ASSERT_FALSE (oDraftsmanHw.DrawBitmap (Bitmap));
}

TEST_F (DraftsmanFixture, CheckTheBitmapValidationInsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationInsideTheScreen");

    LOGI        (MODULE, "Full-screen bitmap");
    EXPECT_CALL (oDraftsmanHw, sendLines (_)).Times (AtLeast (ONE));

    Bitmap.Id         = ZERO;
    Bitmap.Coordinate = { ZERO             , ZERO                 };    // X, Y
    Bitmap.Dimension  = { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY };    // Width, Height
    ASSERT_TRUE (oDraftsmanHw.DrawBitmap (Bitmap));
    
    LOGI (MODULE, "A bitmap on the screen");
    Bitmap.Id         = ZERO;
    Bitmap.Coordinate = { FORTY               , FIFTY             };    // X, Y
    Bitmap.Dimension  = { ONE_HUNDRED         , ONE_HUNDRED       };    // Width, Height
    ASSERT_TRUE (oDraftsmanHw.DrawBitmap (Bitmap));
}

TEST_F (DraftsmanFixture, CheckTheSizeOfDataSentToTheDisplayForTheFullScreenBitmap)
{
    LOGW (MODULE, "CheckTheSizeOfDataSentToTheDisplay");

    EXPECT_CALL (oDraftsmanHw, sendLines (_)).Times (TWENTY_TWO);

    Bitmap.Id         = ZERO;
    Bitmap.Coordinate = { ZERO             , ZERO                 };    // X, Y
    Bitmap.Dimension  = { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY };    // Width, Height
    ASSERT_TRUE (oDraftsmanHw.DrawBitmap (Bitmap));
}

TEST_F (DraftsmanFixture, CheckTheSizeOfDataSentToTheDisplayForTheSmallBitmap)
{
    LOGW (MODULE, "CheckTheSizeOfDataSentToTheDisplayForTheSmallBitmap");

    EXPECT_CALL (oDraftsmanHw, sendLines (_)).Times (ONE);

    Bitmap.Id         = ZERO;
    Bitmap.Coordinate = { ZERO, ZERO };                                 // X, Y
    Bitmap.Dimension  = { FIVE, FIVE };                                 // Width, Height
    ASSERT_TRUE (oDraftsmanHw.DrawBitmap (Bitmap));
}

TEST_F (DraftsmanFixture, CheckTheNumberOfChunksSentToTheDisplay)
{
    LOGW    (MODULE, "CheckTheNumberOfChunksSentToTheDisplay");

    ON_CALL (oDraftsmanHw, calculate (_)).WillByDefault (Invoke (&oDraftsmanHw, &DraftsmanHw::Calculate));

    uint8_t dataChunksLen = ONE;
    for (const auto & calc : CalculationsMatcher)
    {
        class Bitmap bitmap;
        bitmap.Dimension = { calc.second.first, calc.second.second };
        ASSERT_EQ (oDraftsmanHw.Calculate (bitmap.Dimension), dataChunksLen++);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
