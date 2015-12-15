## Update

[ASN.1 Playground](http://asn1-playground.oss.com) added CAM and DENM definitions to their default schemes.
This is an easy and accessible way to determine the size of a CAM and test different payload configurations and, thus, deprecates this repo.

## Information

This parses the ASN.1 notation of a Cooperative Awareness Message (CAM) as defined in ETSI ITS-G5.
The code depends on ``asn1c`` and ``libtasn1``.

``cam_size`` creates a minimal CAM and outputs its size.
Change this file to create CAMs with different contents, i.e. optional items, low frequency information etc.

Please see http://www.bastibl.net/etsi-cams/ for the motivation and further information.

## Output


```
$ ./cam_size
CAM ::= {
    header: ItsPduHeader ::= {
        protocolVersion: 0
        messageID: 0
        stationID: 0
    }
    cam: CoopAwareness ::= {
        generationDeltaTime: 0
        camParameters: CamParameters ::= {
            basicContainer: BasicContainer ::= {
                stationType: 0
                referencePosition: ReferencePosition ::= {
                    latitude: 0
                    longitude: 0
                    positionConfidenceEllipse: PosConfidenceEllipse ::= {
                        semiMajorConfidence: 0
                        semiMinorConfidence: 0
                        semiMajorOrientation: 0
                    }
                    altitude: Altitude ::= {
                        altitudeValue: 0
                        altitudeConfidence: 0
                    }
                }
            }
            highFrequencyContainer: BasicVehicleContainerHighFrequency ::= {
                heading: Heading ::= {
                    headingValue: 0
                    headingConfidence: 1
                }
                speed: Speed ::= {
                    speedValue: 0
                    speedConfidence: 1
                }
                driveDirection: 0
                vehicleLength: VehicleLength ::= {
                    vehicleLengthValue: 1
                    vehicleLengthConfidenceIndication: 0
                }
                vehicleWidth: 1
                longitudinalAcceleration: LongitudinalAcceleration ::= {
                    longitudinalAccelerationValue: 0
                    longitudinalAccelerationConfidence: 0
                }
                curvature: Curvature ::= {
                    curvatureValue: 0
                    curvatureConfidence: 0
                }
                curvatureCalculationMode: 0
                yawRate: YawRate ::= {
                    yawRateValue: 0
                    yawRateConfidence: 0
                }
            }
        }
    }
}
Total size: 327 bits   41 bytes
```

