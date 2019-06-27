#pragma once

#include <GCS_MAVLink/GCS.h>
#include "GCS_Mavlink.h"

class GCS_Tracker : public GCS
{
    friend class Tracker; // for access to _chan in parameter declarations
    friend class GCS_MAVLINK_Tracker;

public:

    // return the number of valid GCS objects
    uint8_t num_gcs() const override { return ARRAY_SIZE(_chan); };

    // return GCS link at offset ofs
    GCS_MAVLINK_Tracker &chan(uint8_t ofs) override {
        if (ofs >= num_gcs()) {
            AP::internalerror().error(AP_InternalError::error_t::gcs_offset);
            ofs = 0;
        }
        return _chan[ofs];
    }
    const GCS_MAVLINK_Tracker &chan(uint8_t ofs) const override {
        if (ofs >= num_gcs()) {
            AP::internalerror().error(AP_InternalError::error_t::gcs_offset);
            ofs = 0;
        }
        return _chan[ofs];
    }

    void update_vehicle_sensor_status_flags() override;

    uint32_t custom_mode() const override;
    MAV_TYPE frame_type() const override;

private:

    void request_datastream_position(uint8_t sysid, uint8_t compid);
    void request_datastream_airpressure(uint8_t sysid, uint8_t compid);

    GCS_MAVLINK_Tracker _chan[MAVLINK_COMM_NUM_BUFFERS];

};
