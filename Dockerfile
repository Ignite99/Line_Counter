# Make sure when doing this your end of line sequence is in LF
FROM gcc:latest

# Create and set the working directory
WORKDIR /app

# Copy your manager script into the container
COPY manager.sh /app/manager.sh

# Make sure the script is executable
RUN chmod +x /app/manager.sh

# Define the default command
CMD ["/app/manager.sh"]