from setuptools import find_packages, setup

package_name = 'handshake_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        (
            'share/ament_index/resource_index/packages',
            ['resource/' + package_name]
        ),
        (
            'share/' + package_name,
            ['package.xml']
        ),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='MANAS',
    maintainer_email='kariamanas7@gmail.com',
    description='Handshake communication between AI and VCU using rclpy',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'ai_node = handshake_pkg.ai_node:main',
            'vcu_node = handshake_pkg.vcu_node:main',
        ],
    },
)
