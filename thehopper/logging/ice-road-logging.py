def iceroad_logging(log_dir, debug, log_prefix = 'las2uncorrectedDEM' ):
    os.makedirs(log_dir, exist_ok= True)

    old_logs = glob(join(log_dir, f'{log_prefix}*.log'))
    if old_logs:
        vnum = max([int(basename(i).split('.')[0].split('-')[-1].replace('r','')) for i in sorted(old_logs)]) + 1
    else:
        vnum = 1

    logging.basicConfig(level=logging.INFO,
    format=f"(ice-road-copters {__name__} %(levelname)s) %(message)s",
    handlers=[
        logging.FileHandler(join(log_dir, f'{log_prefix}-r{vnum}.log')),
        logging.StreamHandler(sys.stdout)]
    )
    log = logging.getLogger(__name__)
    if debug:
        log.setLevel(logging.DEBUG)
    
    return log