import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class AINode(Node):

    def __init__(self):
        super().__init__('ai_node')

        self.publisher_ = self.create_publisher(
            String,
            'AI2VCU',
            10
        )

        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = "AI working"
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: "{msg.data}"')
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    ai_node = AINode()
    rclpy.spin(ai_node)

    ai_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
