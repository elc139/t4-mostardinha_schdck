// Simulação de propagação de vírus.
// Adaptada de um código proposto por David Joiner (Kean University).
//
// Uso: virusim <tamanho-da-populacao> <nro. experimentos> <probab. maxima> 

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "src/Random.h"
#include "src/Population.h"

void checkCommandLine(int argc, char** argv, int& size, int& trials, int& probs)
{
   if (argc > 1) {
      size = atoi(argv[1]);
   }   
   if (argc > 2) {
      trials = atoi(argv[2]);
   }
   if (argc > 3) {
      probs = atoi(argv[3]);
   }   
}

long wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec*1000000 + t.tv_usec;
}

int main(int argc, char* argv[]) 
{
   // parâmetros dos experimentos
   int population_size = 100;
   int amount_of_trials = 250;
   int max_probability = 101;

   double* percent_infected;        // percentuais de infectados (saída)
   double* probability_of_spread;   // probabilidades a serem testadas (entrada)
   double probability_min = 0.0;
   double probability_max = 1.0;
   double probality_step;
   int base_seed = 100;

   long start_time, end_time;

   checkCommandLine(argc, argv, population_size, amount_of_trials, max_probability);
    
   try {
      probability_of_spread = new double[max_probability];
      percent_infected = new double[max_probability];

      probality_step = (probability_max - probability_min)/(double)(max_probability-1);

      printf("Probabilidade\tPercentual Infectado\n");

      // Para cada probabilidade, calcula o percentual de pessoas infectadas
      start_time = wtime();

      #pragma omp parallel for schedule(static) num_threads(2)
      for (int current_probability = 0; current_probability < max_probability; current_probability++) {
         Random rand;

         probability_of_spread[current_probability] = probability_min + (double) current_probability * probality_step;
         percent_infected[current_probability] = 0.0;
         rand.setSeed(base_seed + current_probability); // nova sequência de números aleatórios

         // Executar vários experimentos para a mesma probabilidade
         #pragma omp parallel for schedule(static) num_threads(2)
         for (int current_trial = 0; current_trial < amount_of_trials; current_trial++) {
            // Infecta pessoas até não ter mais ninguém para infectar
            Population* population = new Population(population_size);

            population->propagateUntilOut(population->centralPerson(), probability_of_spread[current_probability], rand);
            percent_infected[current_probability] += population->getPercentInfected();
         }

         // Calcula média dos percentuais de pessoas contaminadas
         percent_infected[current_probability] /= amount_of_trials;

         printf("\n%lf\t\t%lf\n", probability_of_spread[current_probability], percent_infected[current_probability]);
      }
      end_time = wtime();

      printf("%ld msec\n", (long) (end_time - start_time) / 1000);

      delete[] probability_of_spread;
      delete[] percent_infected;
   }
   catch (std::bad_alloc)
   {
      std::cerr << "Erro: alocacao de memoria" << std::endl;
      return 1;
   }

   return 0;
}

