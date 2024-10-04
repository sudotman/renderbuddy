import unreal

def render_sequence(output_path):
    queue = unreal.MoviePipelineQueueSubsystem().get_queue()
    job = queue.allocate_new_job(unreal.MoviePipelineExecutorJob)
    job.sequence = unreal.SoftObjectPath("/Game/Sequences/MySequence")
    job.map = unreal.SoftObjectPath("/Game/Maps/MyMap")
    job.job_name = "RenderJob"
    settings = job.get_configuration().find_or_add_setting_by_class(unreal.MoviePipelineOutputSetting)
    settings.output_directory = unreal.DirectoryPath(output_path)
    executor = unreal.MoviePipelinePIEExecutor()
    executor.execute(queue)

render_sequence("C:/MyRenders/Render_1")
