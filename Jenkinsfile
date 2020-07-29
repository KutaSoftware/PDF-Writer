@Library('bowie-jenkins-pipeline-lib') _
bowiePipeline{
    cloud = 'kubernetes-ms'
    dockerImage = 'valida-ci:2.1.0'
    registryUrl = 'repo.gradiant.org:9026'
    registryCredentialsId = 'Nexus'
    requestMemory = '1G'
    limitMemory = '2G'
    requestCpu = '1'
    limitCpu = '2'
    omitDocumentation = true
    omitTest = true
    omitCoverage = true
}
