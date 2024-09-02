# Use a base image with necessary tools
FROM gcc:latest

# Create and set the working directory
WORKDIR /app

# Copy your manager script into the container
COPY manager.sh /app/manager.sh

# Make sure the script is executable
RUN chmod +x /app/manager.sh

# Define the default command
CMD ["/app/manager.sh"]