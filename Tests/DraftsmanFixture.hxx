#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <utility>
#include "Draftsman.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DraftsmanFixture : public ::testing::Test
{
    public:
        static constexpr char *     MODULE = (char *)"DraftsmanFixture";
        const DraftsmanHw::Config_t Config = { FIFTEEN, { TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY } };    //LinesPerTransfer, Dimensions { Width, Height }
        Font                        Font;
        SpiHw                       SpiHw;
        Bitmap                      Bitmap;
        DraftsmanHw                 DraftsmanHw;

        const std::map <uint8_t, std::pair <uint16_t, uint16_t>> CalculationsMatcher;

        DraftsmanFixture () : DraftsmanHw (Config, SpiHw, Font),
                              CalculationsMatcher { { ONE       , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, FIFTEEN                 ), },
                                                    { TWO       , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, THIRTY                  ), },
                                                    { THREE     , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, FORTY_FIVE              ), },
                                                    { FOUR      , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, SIXTY                   ), },
                                                    { FIVE      , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, SEVENTY_FIVE            ), },
                                                    { SIX       , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, NINTY                   ), },
                                                    { SEVEN     , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_FIVE        ), },
                                                    { EIGHT     , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_TWENTY      ), },
                                                    { NINE      , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_THIRTY_FIVE ), },
                                                    { TEN       , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_FIFTY       ), },
                                                    { ELEVEN    , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_SIXTY_FIVE  ), },
                                                    { TWELVE    , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_EIGHTY      ), },
                                                    { THIRTEEN  , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, ONE_HUNDRED_NINTY_FIVE  ), },
                                                    { FOURTEEN  , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, TWO_HUNDRED_TEN         ), },
                                                    { FIFTEEN   , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, TWO_HUNDRED_TWENTY_FIVE ), },
                                                    { SIXTEEN   , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, TWO_HUNDRED_FORTY       ), },
                                                    { SEVENTEEN , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, TWO_HUNDRED_FIFTY_FIVE  ), },
                                                    { EIGHTEEN  , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, TWO_HUNDRED_SEVENTY     ), },
                                                    { NINETEEN  , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, TWO_HUNDRED_EIGHTY_FIVE ), },
                                                    { TWENTY    , std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, THREE_HUNDRED           ), },
                                                    { TWENTY_ONE, std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, THREE_HUNDRED_FIFTEEN   ), },
                                                    { TWENTY_TWO, std::make_pair <uint16_t, uint16_t> (TWO_HUNDRED_FORTY, THREE_HUNDRED_TWENTY), }
        }
        { }

        ~DraftsmanFixture () = default;

        void TestBody () override { }
        void SetUp    () override { }
        void TearDown () override { }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////