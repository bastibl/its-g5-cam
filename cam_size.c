#include <stdio.h>
#include <sys/types.h>
#include <CAM.h>
#include <errno.h>

static int write_out(const void *buffer, size_t size, void *app_key) {
    FILE *out_fp = app_key;
    size_t wrote = fwrite(buffer, 1, size, out_fp);
    return (wrote == size) ? 0 : -1;
}

int main(int ac, char **av) {

    CAM_t *cam = calloc(1, sizeof(CAM_t));
    if(!cam) {
        perror("calloc() failed");
        exit(1);
    }
    asn_enc_rval_t erv; // encoder return value

    // initialize struct
    cam->cam.camParameters.basicContainer.referencePosition.positionConfidenceEllipse.semiMajorOrientation.headingConfidence = 1;
    cam->cam.camParameters.highFrequencyContainer.present = HighFrequencyContainer_PR_basicVehicleContainerHighFrequency;
    cam->cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency.heading.headingConfidence = 1;
    cam->cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency.speed.speedConfidence = 1;
    cam->cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency.vehicleLength.vehicleLengthValue = 1;
    cam->cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency.vehicleWidth = 1;
    
    /* 
     * encode
     *
     * Unaligned packed encoding rules (PER) as defined in
     * Recommendation ITU-T X.691/ISO/IEC 8825-2 [4] shall
     * be used for CAM encoding and decoding.
     *
     * ETSI EN 302 637-2 V1.3.2 (2014-11)
     */
    erv = uper_encode(&asn_DEF_CAM, cam, write_out, stdout);
    fprintf(stdout, "\n");
    if(erv.encoded == -1) {
        fprintf(stderr, "Cannot encode %s: %s\n", erv.failed_type->name, strerror(errno));
    }

    // print structure
    asn_fprint(stdout, &asn_DEF_CAM, cam);
    fprintf(stdout, "Total size: %zD bytes\n", erv.encoded);

    return 0;
}

