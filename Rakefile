require 'rake/clean'


CLOBBER.include("tmp")

namespace :env do
  1.upto(8) do |n|
    desc "Set CONAN_CPU_COUNT to #{n}"
    task "cpu_count_#{n}".to_sym do 
      ENV['CONAN_CPU_COUNT'] = "#{n}"
    end
  end
end

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
    cmd <<  "--force"
    sh cmd.join(" ")
  end

  desc "6) Test test..."
  task :test do
    cmd = []
    cmd << "conan test test_package  llvm/8.0.0@woidpointer/testing"
    sh cmd.join(" ")
  end

  desc "create a stable package"
  task :create_stable do
    cmd = []
    cmd <<  "conan create . woidpointer/stable"
    sh cmd.join(" ")
  end

end



