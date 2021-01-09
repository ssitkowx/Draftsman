///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "LoggerMock.h"
#include "gmock/gmock.h"
#include "BitmapMock.hxx"
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
    BitmapMock.Id         = ZERO;
    BitmapMock.Coordinate = { ONE                 , ZERO              };    // X, Y
    BitmapMock.Dimension  = { THREE_HUNDRED_TWENTY, TWO_HUNDRED_FORTY };    // Width, Height
    ASSERT_FALSE (DraftsmanMock.DrawBitmap (BitmapMock));

    LOGI (MODULE, "The bitmap will exceed the height of the screen");
    BitmapMock.Id         = ZERO;
    BitmapMock.Coordinate = { ZERO                , ONE               };    // X, Y
    BitmapMock.Dimension  = { THREE_HUNDRED_TWENTY, TWO_HUNDRED_FORTY };    // Width, Height
    ASSERT_FALSE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheBitmapValidationInsideTheScreen)
{
    LOGW (MODULE, "CheckTheBitmapValidationInsideTheScreen");

    LOGI        (MODULE, "Full-screen bitmap");
    EXPECT_CALL (DraftsmanMock, sendLines (_)).Times (AtLeast (ONE));

    BitmapMock.Id         = ZERO;
    BitmapMock.Coordinate = { ZERO             , ZERO                 };    // X, Y
    BitmapMock.Dimension  = { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY };    // Width, Height
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
    
    LOGI (MODULE, "A bitmap on the screen");
    BitmapMock.Id         = ZERO;
    BitmapMock.Coordinate = { FORTY               , FIFTY             };    // X, Y
    BitmapMock.Dimension  = { ONE_HUNDRED         , ONE_HUNDRED       };    // Width, Height
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheSizeOfDataSentToTheDisplayForTheFullScreenBitmap)
{
    LOGW (MODULE, "CheckTheSizeOfDataSentToTheDisplay");

    EXPECT_CALL (DraftsmanMock, sendLines (_)).Times (TWENTY_TWO);

    BitmapMock.Id         = ZERO;
    BitmapMock.Coordinate = { ZERO             , ZERO                 };    // X, Y
    BitmapMock.Dimension  = { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY };    // Width, Height
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheSizeOfDataSentToTheDisplayForTheSmallBitmap)
{
    LOGW (MODULE, "CheckTheSizeOfDataSentToTheDisplayForTheSmallBitmap");

    EXPECT_CALL (DraftsmanMock, sendLines (_)).Times (ONE);

    BitmapMock.Id         = ZERO;
    BitmapMock.Coordinate = { ZERO, ZERO };                                 // X, Y
    BitmapMock.Dimension  = { FIVE, FIVE };                                 // Width, Height
    ASSERT_TRUE (DraftsmanMock.DrawBitmap (BitmapMock));
}

TEST_F (DraftsmanFixture, CheckTheNumberOfChunksSentToTheDisplay)
{
    LOGW    (MODULE, "CheckTheNumberOfChunksSentToTheDisplay");

    ON_CALL (DraftsmanMock, calculate (_)).WillByDefault (Invoke (&DraftsmanMock, &DraftsmanMock::Calculate));

    uint8_t dataChunksLen = ONE;
    for (const auto & calc : CalculationsMatcher)
    {
        Bitmap bitmap;
        bitmap.Dimension = { calc.second.first, calc.second.second };
        ASSERT_EQ (DraftsmanMock.Calculate (bitmap.Dimension), dataChunksLen++);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////