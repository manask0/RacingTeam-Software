import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/townperson/Documents/TraineeSoftwareModule/CheckpointWS/install/handshake_pkg'
