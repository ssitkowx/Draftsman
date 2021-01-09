#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include "Utils.h"
#include "Bitmap.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class Draftsman
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        struct Config_t
        {
            uint16_t           LinesPerTransfer;
            Bitmap::Dimensions Dimension;
        };

        explicit Draftsman  (const Config_t v_config) : config (v_config) { }
        void     DrawText   (std::string_view v_text, const Bitmap::Coordinates v_coordinates) { derivedType.DrawText (v_text, v_coordinates); }
        bool     DrawBitmap (Bitmap v_bitmap)
        {
            if (validate (v_bitmap) == false) { return false; }

            const uint8_t maxRects = calculate (v_bitmap.Dimension);
            if (maxRects == ONE) { sendLines (v_bitmap); }
            else
            {
                uint16_t height             = ZERO;
                const uint16_t bitmapHeight = v_bitmap.Dimension.Height;
                for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
                {
                    if (rectNum == maxRects) { height = bitmapHeight - (rectNum - ONE) * height; }
                    else                     { height = config.LinesPerTransfer * config.Dimension.Width / v_bitmap.Dimension.Width; }

                    auto enableChunkMovement    = [&]() -> bool { return (rectNum == ONE) ? false : true; };
                    bool isChunkMovementEnabled = enableChunkMovement ();
                    v_bitmap.Dimension.Height   = height;
                    v_bitmap.Coordinate.Y       = v_bitmap.Coordinate.Y + isChunkMovementEnabled * height;
                    v_bitmap.Data               = &v_bitmap.Data [isChunkMovementEnabled * v_bitmap.Dimension.Width * height];

                    sendLines (v_bitmap);
                }
            }

            return true;
        };

    protected:
        void sendLines (const Bitmap & v_rect) { derivedType.sendLines (v_rect); }

    private:
        const Config_t config;

        bool validate (const Bitmap & v_bitmap) const
        {
            return (((v_bitmap.Coordinate.X + v_bitmap.Dimension.Width) > config.Dimension.Width) ||
                    ((v_bitmap.Coordinate.Y + v_bitmap.Dimension.Height) > config.Dimension.Height)) ? false : true;
        }

        uint8_t calculate (const Bitmap::Dimensions & v_dimensions) const
        {
            const double  rects         = (v_dimensions.Width * v_dimensions.Height) / (config.Dimension.Width * config.LinesPerTransfer);
            const double  aditionalRect = (v_dimensions.Width * v_dimensions.Height) % (config.Dimension.Width * config.LinesPerTransfer);
            uint8_t maxRects            = static_cast <uint8_t> (rects);
            return (aditionalRect > ZERO) ? ++maxRects : maxRects;
        }

        ~Draftsman () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
