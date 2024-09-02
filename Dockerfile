# Make sure when doing this your end of line sequence is in LF
FROM gcc:latest

# Created the working directory
WORKDIR /app

# Copied my script into the container
COPY manager.sh /app/manager.sh

# Ensure script is executable
RUN chmod +x /app/manager.sh

# Define default command
CMD ["/app/manager.sh"]