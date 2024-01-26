import shlex
import subprocess

def cl_call(command, log):
    """
    Runs shell commands in python and returns output
    Got this from a stack overflow but can't find it now...

    Parameters:
    command (str or list): list of commands. if string is passed we will try and
    parse to list using shelex
    """
    if type(command) == str:
        command = shlex.split(command)
    log.info('Subprocess: "' + ' '.join(command) + '"')

    process = subprocess.Popen(command, 
                           stdout=subprocess.PIPE,
                           universal_newlines=True)

    while True:
        output = process.stdout.readline()
        log.info(output.strip())
        # Do something else
        return_code = process.poll()
        if return_code is not None:
            log.info(f'RETURN CODE {return_code}')
            # Process has finished, read rest of the output 
            for output in process.stdout.readlines():
                log.info(output.strip())
            break