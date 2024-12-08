# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc
import warnings

import image_service_pb2 as image__service__pb2

GRPC_GENERATED_VERSION = '1.66.1'
GRPC_VERSION = grpc.__version__
_version_not_supported = False

try:
    from grpc._utilities import first_version_is_lower
    _version_not_supported = first_version_is_lower(GRPC_VERSION, GRPC_GENERATED_VERSION)
except ImportError:
    _version_not_supported = True

if _version_not_supported:
    raise RuntimeError(
        f'The grpc package installed is at version {GRPC_VERSION},'
        + f' but the generated code in image_service_pb2_grpc.py depends on'
        + f' grpcio>={GRPC_GENERATED_VERSION}.'
        + f' Please upgrade your grpc module to grpcio>={GRPC_GENERATED_VERSION}'
        + f' or downgrade your generated code using grpcio-tools<={GRPC_VERSION}.'
    )


class ImageServiceStub(object):
    """定义ImageService服务，包含GetImage方法
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.GetImage = channel.unary_unary(
                '/imageservice.ImageService/GetImage',
                request_serializer=image__service__pb2.ImageRequest.SerializeToString,
                response_deserializer=image__service__pb2.ImageResponse.FromString,
                _registered_method=True)


class ImageServiceServicer(object):
    """定义ImageService服务，包含GetImage方法
    """

    def GetImage(self, request, context):
        """GetImage 方法接收一个 ImageRequest 请求，返回一个 ImageResponse 响应
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ImageServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'GetImage': grpc.unary_unary_rpc_method_handler(
                    servicer.GetImage,
                    request_deserializer=image__service__pb2.ImageRequest.FromString,
                    response_serializer=image__service__pb2.ImageResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'imageservice.ImageService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('imageservice.ImageService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ImageService(object):
    """定义ImageService服务，包含GetImage方法
    """

    @staticmethod
    def GetImage(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/imageservice.ImageService/GetImage',
            image__service__pb2.ImageRequest.SerializeToString,
            image__service__pb2.ImageResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
