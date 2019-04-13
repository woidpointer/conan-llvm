

namespace :conan do
  desc "1) Test source..."
  task :source do
    sh "conan source . --source-folder=tmp/source"
  end


  desc "2) Test install..."
  task :install do
    sh "conan install . --install-folder=tmp/build"
  end

  desc "3) Test build..."
  task :build do
    start_time = Time.now
    sh "conan build . --source-folder=tmp/source  --build-folder=tmp/build"
    end_time = Time.now
    puts("Execution duration: #{end_time - start_time}")
  end

  desc "4) Test package..."
  task :package do
    sh "conan package . --source-folder=tmp/source --build-folder=tmp/build --package-folder=tmp/package"
  end

  desc "5) Test export package..."
  task :export do
    cmd = []
    cmd << "conan export-pkg . woidpointer/testing"
    cmd <<  "--source-folder=tmp/source --build-folder=tmp/build"
    sh cmd.join(" ")
  end



end



